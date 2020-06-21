import Vue from 'vue'
import upperFirst from 'lodash/upperFirst'
import camelCase from 'lodash/camelCase'

// 通过require.context方法，
// 打造一个转着全局组件文件名列表map容器
const requireComponent = require.context('./components', false, /Base[A-Z]\w+\.(vue|js)$/)

//用map容器遍历的方式遍历内一个context中的文件
requireComponent.keys().forEach(fileName => {
  // 获取组件文件名
  const componentConfig = requireComponent(fileName)

  const componentName = upperFirst(
    camelCase(
      fileName
        .split('/')
        .pop()
        .replace(/\.\w+$/, '')
    )
    //componentName:./components/aaa.vue => aaa
  )

  // 全局注册组件
  Vue.component(
    componentName,
    // 优先`export default`，否则就模块根
    componentConfig.default || componentConfig
  )
})