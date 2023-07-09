use std::task::Context;

use raw_window_handle::HasRawWindowHandle;

use winit::{
    event::{Event, WindowEvent, VirtualKeyCode},
    event_loop::EventLoop,
    window::{WindowBuilder},
};

use glutin::{
    context::{ContextAttributesBuilder, ContextAttributes, ContextApi, Version},
    config::{ConfigTemplateBuilder, GlConfig, Config},
    display::{GetGlDisplay, GlDisplay}
};
use glutin_winit::DisplayBuilder;



fn main() {
    let event_loop = EventLoop::new();
    let (window, gl_config);
    // set window and gl_config
    {
        // window builder
        let mut builder = WindowBuilder::new();
        builder = builder.with_title("Starting title");
        
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
        window = tmp.unwrap();
    }
    let raw_window_handle = window.raw_window_handle();
    let display = gl_config.display();
    let not_current_gl_context;
    {
        let context_attribs = ContextAttributesBuilder::new().build(Some(raw_window_handle));
        not_current_gl_context = unsafe { //unsafe because raw_window_handle MUST be safe
            display.create_context(&gl_config, &context_attribs).unwrap_or_else(|_| { // try modern opengl
                let context_attribs_fallback =  ContextAttributesBuilder::new().with_context_api(ContextApi::Gles(None)).build(Some(raw_window_handle)); // try gles 
                display.create_context(&gl_config, &context_attribs_fallback).unwrap_or_else(|_| { // try old compatibility mode
                    let context_attribs_legacy = ContextAttributesBuilder::new().with_context_api(ContextApi::OpenGl(Some(Version::new(2, 1)))).build(Some(raw_window_handle));
                    display.create_context(&gl_config, &context_attribs_legacy).expect("Failed to create context")
                })
            })
        };
    }


    println!("Picked a config with {} samples", gl_config.num_samples());
    

    event_loop.run(move |event, _, control_flow| {
        control_flow.set_poll();

        // control_flow.set_wait(); // can be used for menu
    
        match event {
            Event::WindowEvent {
                event: WindowEvent::CloseRequested,
                ..
            } => {
                println!("The close button was pressed; stopping");
                control_flow.set_exit();
            },
            Event::WindowEvent {
                event: WindowEvent::KeyboardInput {
                    input: ref x,
                    ..
                },
                ..
            } => {
                match x.virtual_keycode {
                    Some(y) => {
                        match y{ 
                            VirtualKeyCode::Escape => {
                                println!("Escaped!");
                                control_flow.set_exit();
                            },
                            _ => {}
                        }
                    },
                    _ => {}
                }
            }
            Event::MainEventsCleared => {
                // Application update code.
                window.request_redraw();
            },
            Event::RedrawRequested(_) => {
                // can be used for menu
            },
            _ => ()
        }
    });
}