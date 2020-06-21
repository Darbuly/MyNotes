
1. await用在字面量中是失效的！它不能再写字面量的时刻暂停去执行await的promise的同时又可以保持
 ctx.body = {
     data: await hello(); //
  };

2. await的优先级
const text = await getData().text; // 报错！因为await的优先级要小于 . 运算符
const text = (await getData()).text;

3. 不可await调用当作函数实参传递
// 错误写法
save(await getData());
// 正确写法
const data = await getData();
save(data);