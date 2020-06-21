> 使用 class 的语法，让开发者告别了使用 prototype 模仿面向对象的时代。但注意，它不是新类型，typeof解析只是一个function,故它只是原型模仿面向对象开发用的语法糖
# 1. 语法 #
    class name [extends] {
      // class body
    }

# 2. 特性 #

    class Human {
    	says(){console.log("say something!")}
    }
    var p = new Human();
    p.says()

**结论1：构造函数constructor可有可无。**  
**结论2：方法的定义是解耦的**（不需要 xxx.method=function(){...}这样定义）  



普通函数声明可以被提升，被提升的函数声明我们可以先行访问该函数再对它进行声明，

    var p = new Person()
    function Person(){
    	this.say = function () {console.log("say something!")}
    }
	//不报错


而class类声明不能被提升，所以class类使用前必须先被声明  

	var p = new Person()
    class Person{
    	say(){console.log("say something!")}
    }
	//报错：1 Uncaught ReferenceError: Person is not defined  

**结论3：类声明不可以提升（这与函数声明不同）。**  




# 3. 继承 #
## 3.1 extends 关键字 ##
用来声明要继承的父类

    class Cat extends Animal {
    	constructor() {
    	}
    	...
    }
## 3.2 super关键字   ##
用于访问和调用父对象上的构造函数

注意，子类没有自己的this对象，而是继承父类的this对象，然后对其进行加工。所以，如果不调用super方法，子类就得不到this对象  
**结论4：子类在访问使用this前必须先在constructor方法里调用super方法。**

# 4. HelloWorld挑战 #
手写一个简单的class，然后实例化一个具体的对象。
> 需求：  
> 创建一个类，叫Animal，里面有动物类型的属性type，有说话的方法“<type说了一句"helloClass!"”,要求创建一个子类cat，并说话。


    class Animal{
    	constructor(){
    		this.type = 'Animal'
    	}
    	says(){
    		console.log(this.type+"说了一句 helloClass!")
    	}
    }
    class Cat extends Animal{
    	constructor(){
    		super()
    		this.type = "cat"
    	}
    }
    
    var c = new Cat()
    c.says()