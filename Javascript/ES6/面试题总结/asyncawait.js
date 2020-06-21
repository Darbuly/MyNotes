async function async1(){
    console.log('async1 start')
    await async2()
    console.log('async1 end')
}
async function async2(){
    console.log('async2')
}
console.log('script start')
setTimeout(function(){
    console.log('setTimeout')
},0)  
async1(); 
new Promise(function(resolve){
    console.log('promise1')
    resolve();
}).then(function(){
    console.log('promise2')
})
console.log('script end')

script start
[setTimeout]
async1 start
async2
[promise.async2]
promise1
[promise.async2,promise1]
script end
[promise1]promise.async2
async1 end
[]promise1
promise2
[]setTimeout
setTimeout




=>
script start
async1 start
async2
promise1
script end
async1 end
promise2
[undefined]
setTimeout

script start
VM111:2 async1 start
VM111:7 async2
VM111:15 promise1
VM111:20 script end
VM111:4 async1 end
VM111:18 promise2
undefined
VM111:11 setTimeout