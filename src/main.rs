use winit::{
    event::{Event, WindowEvent, KeyboardInput, VirtualKeyCode},
    event_loop::EventLoop,
    window::{WindowBuilder, Fullscreen},
};

fn main() {
    let event_loop = EventLoop::new();
    let window;
    {
        let mut builder = WindowBuilder::new();
        //builder = builder.with_resizable(false).with_title("Starting title").with_fullscreen(Some(Fullscreen::Borderless(None))).with_maximized(true);
        
        builder = builder.with_title("Starting title");
        window = builder.build(&event_loop).unwrap();
    }

    event_loop.run(move |event, _, control_flow| {
        control_flow.set_poll();

        // control_flow.set_wait(); // possible for menus
    
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