//堆栈法
var a = [1,2,3,4,56,7,9]
var q = []
for(let i=a.length-1;i>=0;i--){
	q.push(a[i])
}
console.log(q)

//交换法
var a = [1,2,3,4,56,7,9]
for(let i=0;i<a.length/2;i++){
	//arr[0] 换 arr[arr.length-1-0]
	//arr[1] 换 arr[arr.length-1-1]
	//arr[2] 换 arr[arr.length-1-2]
	//。。。
	var temp = a[i]
	a[i] = a[a.length-1-i]
	a[a.length-1-i] = temp
}
console.log(a)


