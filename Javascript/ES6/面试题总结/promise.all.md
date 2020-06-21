# 1. 概述 #
`Promise.all(iterable) `方法返回一个 Promise 实例，
这个实例的完成条件是：



- 要么在 iterable 参数内所有的 promise 都“完成（resolved）”


- 要么在 iterable 参数不包含promise对象时回调完成（resolve）；



如果参数中 ` promise `有一个失败（rejected），此实例回调失败（reject），失败的原因取决于第一个失败 promise 的结果。

# 2. 语法 #
    Promise.all(iterable);

## 2.1 参数 ##
- iterable：一个可迭代对象，要么字符串，要么数组。

## 2.2 返回值 ##


在任何情况下，Promise.all 返回的 promise 的完成状态的结果都是一个数组，它包含所有的传入迭代参数对象的值（也包括非 promise 值）。
如果传入的 promise 中有一个失败（rejected），Promise.all 异步地返回以个回调函数，这个回调函数来自于失败的那个prosmise（或其他）所定义的失败状态下的回调函数，而不在关心别的promise是否完成。

**结论1：如果完成，就是数组，如果失败，就是一个失败状态的回调**

- 如果传入的参数是一个空的可迭代对象(空的迭代就是0)，则返回一个**同步完成（already resolved）（即同步完成）**状态的 Promise。

- 如果传入的参数不包含任何 promise，则返回一个**异步完成（asynchronously resolved）**的 Promise。除了Google Chrome 58 之外。

> 注意：Google Chrome 58 在这种情况下还是会返回一个
**已完成（already resolved）**状态的 Promise。


- 其它情况下返回一个**处理中（pending）**的Promise。


- 返回**处理中（pending）**的Promise 之后会在所有的 promise 都完成就再返回一个**异步完成（asynchronously resolved）**

- 如果有一个 promise 失败时异步地变为**异步失败**。 
- 参数内promise 顺序排列决定了返回值的顺序，而不是由参数内调用 promise 的完成顺序。

**结论2：有两种特殊的完成，一般都是处理，完了之后要么异步完成，要么异步失败。**

# 3. 状态解析 #

## 3.1 完成（Fulfillment） ##


- 如果传入的可迭代对象为空，Promise.all 会同步地返回一个**同步完成（already resolved）**状态的promise。

**结论3：当且仅当传入的可迭代对象为空时为同步**

- 如果所有传入的 promise 都变为完成状态，或者传入的可迭代对象内没有 promise，Promise.all 返回的 promise **异步完成（asynchronously resolved）**。

**结论4：promise.all两种完成状态：同步+异步**



## 3.2 失败/拒绝（Rejection） ##

# 4. HelloWorld挑战#
## 4.1 异步性利用 ##
> 需求：
> 想办法利用异步性，在promise.all的pending状态和fulfilled状态下都能输出promise.all本身，
> 要求输出:
> 
> HelloPromise.all,现在的你是pending状态，输出是：<console.log(promise.all)>
> HelloPromise.all,现在的你是fulfilled状态，输出是：<console.log(promise.all)>

    var mixedPromisesArray = [Promise.resolve(33),Promise.resolve(44)]
    
    var p = Promise.all(mixedPromisesArray)
    
    console.log("HelloPromise.all，现在的你是pending状态，输出是："+p)
    
    setTimeout(()=>{
    	console.log("HelloPromise.all,现在的你是fulfilled状态，输出是："+p)
    })



4.2 所有都完成才执行
> 需求：
> 设置三个异步请求，第一个请求、第二个请求、第三个请求均需要10秒内随机数,在异步之前就分别输出每一个请求所需的描述，当三个请求都完成了之后，才开始执行一个输出“三个请求都完成啦！”
如：  
请求1将在 4.860078951744158秒完成！  
请求2将在 0.9114030901707126秒完成！  
请求3将在 3.2882597999240315秒完成！   
请求1完成了,请求2完成了,请求3完成了 三个请求都完成啦！
    
    var q1 = new Promise((resolve,reject)=>{
    	let time = Math.random()*10000
    	console.log("请求1将在 "+ time/1000.0 + "秒完成！")
    	setTimeout(()=>{resolve("请求1完成了")},time)
    })
    
    var q2 = new Promise((resolve,reject)=>{
    	let time = Math.random()*10000
    	console.log("请求2将在 "+ time/1000.0 + "秒完成！")
    	setTimeout(()=>{resolve("请求2完成了")},time)
    })
    
    var q3 = new Promise((resolve,reject)=>{
    	let time = Math.random()*10000
    	console.log("请求3将在 "+ time/1000.0 + "秒完成！")
    	setTimeout(()=>{resolve("请求3完成了")},time)
    })
    
    var mixedPromiseArray = [q1,q2,q3]
    
    var p = Promise.all(mixedPromiseArray)
    
    p.then(values=>{
    	console.log(values+"三个请求都完成啦！")	
    }).catch(reason=>{
    	console.log(reson)
    })