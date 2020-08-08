/**
 * _asyncToGenerator: 这个函数是 用 Promise 执行 yield 函数，创建 gen执行链 的方式,将异步执行的函数，同步化，按一定的顺序去同步执行，半路出错就 reject ，全部执行完毕就 resolve
 *  如 fn = {
 *  yield fn1()
 *  yield fn2()
 *  yield fn3()
 * }
 */
function _asyncToGenerator(fn) {
    let newFun = function () {
        var self = this,
            args = arguments;


        return new Promise(function (resolve, reject) {
            var gen = fn.apply(self, args); // apply  常用于 替换函数名，保留上下文对象self+函数参数对象args
            // gen = fn 

            function _next(value) {
                asyncGeneratorStep(gen, resolve, reject, _next, _throw, "next", value); //单步执行
            }

            function _throw(err) {
                asyncGeneratorStep(gen, resolve, reject, _next, _throw, "throw", err);
            }
            _next(undefined);
        });
    }
    return newFun;
}


//       asyncGeneratorStep(fn, resolve, reject, _next指针, _throw指针, key：枚举next和throw, arg:fn的实参)
function asyncGeneratorStep(gen, resolve, reject, _next, _throw, key, arg) {
    try {
        var info = gen[key](arg); //var info = gen.next(arg)  执行 fn 下一个 yield
        var value = info.value; //返回值 value
    } catch (error) {
        reject(error);
        return;
    }
    if (info.done) { //如果全部执行完毕了，就 resolve 与 fn 对应的那个Promise对象
        resolve(value);
    } else {
        Promise.resolve(value).then(_next, _throw); //如果没有执行完毕，就临时制造一个新的Promise对象，用于执行下一个gen单元，由此创建gen执行链，这里就像递归  asyncGeneratorStep(gen, resolve, reject, _next, _throw, "next", value)
    }
}

const a = function* () {
    args._ = args._ || []; // shift the command itself   //dev

    if (args._[0] === name) args._.shift(); //args['dev'] => args[]

    _this3.args = args; // _this3.args = ['dev'] it had been empty command.



    yield _this3.init(); //init
    logger.debug('plugins:');
    logger.debug(_this3.plugins);

    _this3.setStage(_enums.ServiceStage.run);

    yield _this3.applyPlugins({
        key: 'onStart',
        type: _enums.ApplyPluginsType.event,
        args: {
            args
        }
    });


    return _this3.runCommand({
        name,
        args
    });
}






return _asyncToGenerator(a)();