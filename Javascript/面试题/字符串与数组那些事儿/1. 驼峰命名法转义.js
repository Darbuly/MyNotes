var foo = 'get-element-by-id'
var arr = foo.split('-')
for(let i in arr){
	if(0!=i){
	arr[i]=arr[i].charAt(0).toUpperCase()+arr[i].substr(1,arr[i].length-1)
	}
}
console.log(arr.join(''))

