use raw_window_handle::HasRawWindowHandle;
use std::ptr;

use std::ffi::{CStr, CString};

use winit::{
    event::{Event, WindowEvent, DeviceEvent, VirtualKeyCode, ElementState},
    event_loop::EventLoop,
    window::{WindowBuilder, Fullscreen},
};

use glutin::{
    context::{ContextAttributesBuilder, ContextApi, Version},
    config::{ConfigTemplateBuilder, GlConfig},
    display::{GetGlDisplay, GlDisplay}, prelude::NotCurrentGlContextSurfaceAccessor
};
use glutin::prelude::GlSurface;

use glutin_winit::{DisplayBuilder, GlWindow};

extern crate gl;
// include the OpenGL type aliases
use gl::{types::*, RenderbufferStorage};


mod renderer;
use renderer::Renderer;

mod camera;
use camera::Camera;

mod mesh;
mod model;

// ANDROID WILL CURRENTLY PROBABLY CRASH. NOT SURE ABOUT IOS


fn main() {
    let event_loop = EventLoop::new();
    let (window, gl_config);
    // set window and gl_config
    {
        // window builder
        let mut builder = WindowBuilder::new();
        builder = builder.with_title("Starting title");//.with_fullscreen(Some(Fullscreen::Borderless(None)));
        
        //context template builder -> configuration for the context
        let context_builder = ConfigTemplateBuilder::new();

        //config picker, copied from example, idk what this is

        // display builder
        let mut display_builder = DisplayBuilder::new();
        display_builder = display_builder.with_window_builder(Some(builder));
        
        let tmp;
        (tmp, gl_config) = display_builder.build(&event_loop, context_builder,  //third parameter is copied, idk what it does exactly
            |configs| {configs
                .reduce(|accum, config| {
                    let transparency_check = config.supports_transparency().unwrap_or(false)
                        & !accum.supports_transparency().unwrap_or(false);

                    if transparency_check || config.num_samples() > accum.num_samples() {
                        config
                    } else {
                        accum
                    }
                })
                .unwrap()
        }).unwrap();

        //will panic if window is not created yet (on some platforms ex. Android)
        window = tmp.unwrap();
    }
    let raw_window_handle = window.raw_window_handle();
    let display = gl_config.display();
    let mut not_current_gl_context;
    {
        let context_attribs = ContextAttributesBuilder::new().build(Some(raw_window_handle));
        not_current_gl_context = unsafe {Some(//unsafe because raw_window_handle MUST be safe
            display.create_context(&gl_config, &context_attribs).unwrap_or_else(|_| { // try modern opengl
                let context_attribs_fallback =  ContextAttributesBuilder::new().with_context_api(ContextApi::Gles(None)).build(Some(raw_window_handle)); // try gles 
                display.create_context(&gl_config, &context_attribs_fallback).unwrap_or_else(|_| { // try old compatibility mode
                    let context_attribs_legacy = ContextAttributesBuilder::new().with_context_api(ContextApi::OpenGl(Some(Version::new(2, 1)))).build(Some(raw_window_handle));
                    display.create_context(&gl_config, &context_attribs_legacy).expect("Failed to create context")
                })
            })
        )};
    }
    
    
    println!("Picked a config with {} samples", gl_config.num_samples());
    
    
    let mut state = None; 
    let mut renderer = None;

    //create camera
    let mut camera = Camera::new_from_position(0.0, 0.0, -5.0);
    event_loop.run(move |event, _, control_flow| {
        control_flow.set_poll();

        // control_flow.set_wait(); // can be used for menu
    
        match event {        
            Event::Resumed => {
                #[cfg(android_platform)]
                println!("Android window is just now available");

                // Logic for creating window on platforms where it cannot be created before first resumed call goes here

                // Create window surface
                let window_surface;
                {
                    let window_surface_attribs = window.build_surface_attributes(<_>::default());
                    unsafe {
                        window_surface = display.create_window_surface(&gl_config, &window_surface_attribs).expect("Surface creation failed!");
                    }
                }
                
                // create context
                // make context current and set not_current_gl_context as None
                let context = not_current_gl_context.take().unwrap().make_current(&window_surface).expect("Making context current has failed!"); 
                renderer.get_or_insert_with(|| Renderer::new(&display));

                
                assert!(state.replace((context, window_surface)).is_none());

            },
            Event::Suspended => {
                //only called in android.
            },

            Event::WindowEvent {event, ..} => match event {
                WindowEvent::CloseRequested => {
                    control_flow.set_exit();
                }
                WindowEvent::Resized(size) => {
                    //println!("resized to {:?}", size);
                    if size.width != 0 && size.height != 0 { // resize by hand, EGL requires it
                        // TO IMPLEMENT
                        renderer.as_mut().unwrap().resize_window(size.width as i32, size.height as i32);
                    }
                },
                WindowEvent::KeyboardInput{input, ..} => match input.virtual_keycode.unwrap() {
                    VirtualKeyCode::Escape => {
                        println!("Exiting!");
                        control_flow.set_exit();
                    },
                    _ => {}
                },
                _=>{}
            },
            Event::DeviceEvent {event, ..} => match event {
                DeviceEvent::Key(winit::event::KeyboardInput{state, virtual_keycode, ..}) => {
                    match virtual_keycode.unwrap() {
                        VirtualKeyCode::W  => {
                            camera.forward = state == ElementState::Pressed;
                        },
                        VirtualKeyCode::S => {
                            camera.back = state == ElementState::Pressed;
                        }
                        VirtualKeyCode::A => {
                            camera.right = state == ElementState::Pressed;
                        },
                        VirtualKeyCode::D => {
                            camera.left = state == ElementState::Pressed;
                        }
                        VirtualKeyCode::LControl => {
                            camera.up = state == ElementState::Pressed;
                        },  
                        VirtualKeyCode::Space => {
                            camera.down = state == ElementState::Pressed;
                        },
                        _ => {}
                    }
                },
                DeviceEvent::MouseMotion { delta } => camera.mouseMove(delta),
                _=>{}
            }
            Event::RedrawEventsCleared => {
                
            },
            Event::MainEventsCleared => {
                // Application update code.
                window.request_redraw();
                // queue redraw
            },
            Event::RedrawRequested(_) => {
                if let Some((context, window_surface)) = &state {
                    camera.update_queued_move(); // update queued camera movement
                    renderer.as_mut().unwrap().draw(&window_surface, &context, &mut camera);
                    
                }
            },
            _ => ()
        }
    });
}

