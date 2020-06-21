<template>
	<div>
		<input @keyup.enter="add" type="text" v-model='mytodo'>
		<button @click="chgTitle">改变标题</button>
		<button @click="add" >添加任务</button>
		<button @click="clear">清空</button>
		<Title :ititle="title"></Title>
		<li :class="{'done':v.done}" :style="{'text-decoration':v.done?'line-through':''}" @click="toggle(a)"  v-for="(v,a) in todos">{{a+1}}:{{v.title}}</li>
		<p>{{doneNum}}/{{todos.length}}</p>
	</div>
</template>

<script>
import Title from './Title'
export default{
	components:{
		Title,
	},
	data(){
		return {
		title:"hello Darbuly!",
		show:true,
		mytodo:"",
		todos:[
			{title:'eat',done:false},
			{title:'sleep',done:false},
			{title:'coding',done:false}
			]
		}
	},
	computed:{
		doneNum(){
			return this.todos.filter(v=>v.done).length
		}
	},
	methods:{
		chgTitle(){
			this.title = this.mytodo
		},
		add(){
			this.todos.push({title:this.mytodo,done:false})
			this.mytodo = ''
		},
		toggle(i){
			this.todos[i].done = !this.todos[i].done
		},
		clear(){
			this.todos = this.todos.filter(v=>!v.done)
		}
	}
}
</script>

<style>
	li.done{
		color: red;
	}
</style>