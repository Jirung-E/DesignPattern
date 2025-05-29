use std::rc::Rc;


trait Observer {
    fn receive_update(&self);
}

trait Observee<'a> {
    type Obs;

    fn add_observer(&mut self, observer: Self::Obs);
    fn remove_observer(&mut self, observer_id: usize);
    fn notify_observers(&self);
    fn set_callback<F>(&mut self, callback: F)
    where
        F: Fn(&Self::Obs) + 'a;
}


#[derive(Clone)]
struct Subscriber {
    name: String,
}

impl Subscriber {
    fn new(name: &str) -> Self {
        Subscriber {
            name: name.to_string(),
        }
    }
}

impl Observer for Subscriber {
    fn receive_update(&self) {
        println!("{} has been notified of the update!", self.name);
    }
}


struct Publisher<'a> {
    observers: Vec<Rc<dyn Observer + 'a>>,
    callbacks: Vec<Box<dyn Fn(&Rc<dyn Observer + 'a>) + 'a>>,
}

impl<'a> Publisher<'a> {
    fn new() -> Self {
        Publisher {
            observers: Vec::new(),
            callbacks: Vec::new(),
        }
    }

    fn update(&self) {
        println!("Publisher state updated, notifying observers...");
        self.notify_observers();
    }
}

impl<'a> Observee<'a> for Publisher<'a> {
    type Obs = Rc<dyn Observer + 'a>;

    fn add_observer(&mut self, observer: Self::Obs) {
        self.observers.push(observer);
    }

    fn remove_observer(&mut self, observer_id: usize) {
        if observer_id < self.observers.len() {
            self.observers.remove(observer_id);
        }
    }

    fn notify_observers(&self) {
        for i in 0..self.observers.len() {
            let observer = &self.observers[i];
            observer.receive_update();
            if let Some(callback) = self.callbacks.get(i) {
                callback(observer);
            }
        }
    }

    fn set_callback<F>(&mut self, callback: F)
    where
        F: Fn(&Self::Obs) + 'a,
    {
        self.callbacks.push(Box::new(callback));
    }
}


fn main() {
    println!("Observer Pattern");

    let sub1 = Rc::new(Subscriber::new("Subscriber 1"));
    let sub2 = Rc::new(Subscriber::new("Subscriber 2"));
    let mut publisher = Publisher::new();

    {
        let sub1_clone = Rc::clone(&sub1);
        let sub2_clone = Rc::clone(&sub2);

        publisher.add_observer(sub1_clone);
        publisher.set_callback(move |obs| {
            println!("Callback for Subscriber 1 executed.");
        });
        publisher.add_observer(sub2_clone);
    }
    publisher.update();

    publisher.remove_observer(0);
    publisher.update();

    // publisher에 넣은 Subscriber와 별개로 계속 사용 가능
    println!("sub1.name: {}", sub1.name);
    println!("sub2.name: {}", sub2.name);
}