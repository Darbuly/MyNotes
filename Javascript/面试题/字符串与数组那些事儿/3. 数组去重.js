//set容器法
var a = [1,1,3,4,5,67,8]
var set = new Set(a)
var res = []

for(let i of set){
	res.push(i)
}
console.log(res)

//暴力枚举法
var a = [1,1,3,4,5,67,8]
var newarr = []

//遍历a数组
for(let i=0;i<a.length;i++){
	//遍历newarr数组
	for(let j=0;j<newarr.length;j++){
		if(a[i]==newarr[j]){break} //新数组出现重复了，没必要继续循环

		if(j == newarr.lenth-1){
			newarr.push(a[i])//遍历最后一个都没重复，就进新数组
		}
	}
}
