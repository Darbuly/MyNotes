


let dbl = {
	_name:"小威威",
	get name(){
		return this._name
	},
	set name(val){
		console.log('new name is '+val)
		this._name = val
	}
}
console.log(dbl.name)
dbl.name="Darbuly"
console.log(dbl.name)


