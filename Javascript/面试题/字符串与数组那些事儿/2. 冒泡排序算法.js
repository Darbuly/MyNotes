
var a = [5,4,3,2,1]
var flag = true
//轮数 4
for(let i = 0;i<a.length-1 && flag;i++){
	//次数 4,3,2,1
	for(let j = 0;j<a.length-1-i;j++){
		flag = false
		if(a[j]>a[j+1]){
			flag = true
			let temp = a[j]
			a[j]=a[j+1]
			a[j+1]=temp
		}
	}
}

console.log(a)

