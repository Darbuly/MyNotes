/**
 * 深度优先遍历  预设插件树
 * 
 * @param {*} preset preset单元对象  e.g  {id: '@umijs/preset-built-in', key: 'builtIn', path: 'D:/Wangwenwei/order_admin/client/node_modules/@umijs/preset-built-in/lib/index.js', apply: ƒ, defaultConfig: null}

 */


function initPreset(preset) {
    const id = preset.id,
        key = preset.key,
        apply = preset.apply;
    preset.isPreset = true;

    const api = this.getPluginAPI({
        id,
        key,
        service: this
    }); // 获取插件API： e.g Proxy {id: '@umijs/preset-built-in', key: 'builtIn', service: Service, utils: {…}, Html: ƒ} 


    this.registerPlugin(preset); // 注册插件： e.g Proxy {id: '@umijs/preset-built-in', key: 'builtIn', service: Service, utils: {…}, Html: ƒ} TODO: ...defaultConfigs 考虑要不要支持，可能这个需求可以通过其他渠道实现

    /**
     * 遍历获取子节点
     */
    const _ref = apply()(api) || {},
        presets = _ref.presets,
        plugins = _ref.plugins,
        defaultConfigs = _objectWithoutProperties(_ref, ["presets", "plugins"]); // register extra presets and plugins

    /**
     * 是否有子预设,有的话，递归initPreset
     */
    if (presets) {
        (0, _assert().default)(Array.isArray(presets), `presets returned from preset ${id} must be Array.`); // 插到最前面，下个 while 循环优先执行

        this._extraPresets.splice(0, 0, ...presets.map(path => {
            return (0, _pluginUtils.pathToObj)({
                type: _enums.PluginType.preset,
                path,
                cwd: this.cwd
            });
        }));
    } // 深度优先


    const extraPresets = _utils().lodash.clone(this._extraPresets);

    this._extraPresets = [];

    while (extraPresets.length) {
        this.initPreset(extraPresets.shift());
    }
    /**
     * 是否有子插件,有的话，它的递归不处于这里的，这里是预设递归，故只需要入栈  this._extraPlugins
     */
    if (plugins) {
        (0, _assert().default)(Array.isArray(plugins), `plugins returned from preset ${id} must be Array.`);

        this._extraPlugins.push(...plugins.map(path => {
            return (0, _pluginUtils.pathToObj)({
                type: _enums.PluginType.plugin,
                path,
                cwd: this.cwd
            });
        }));
    }
}



function getPluginAPI(opts) {
    const pluginAPI = new _PluginAPI.default(opts); // register built-in methods

    ['onPluginReady', 'modifyPaths', 'onStart', 'modifyDefaultConfig', 'modifyConfig'].forEach(name => {
        pluginAPI.registerMethod({
            name,
            exitsError: false
        });
    });
    return new Proxy(pluginAPI, {
        get: (target, prop) => {
            // 由于 pluginMethods 需要在 register 阶段可用
            // 必须通过 proxy 的方式动态获取最新，以实现边注册边使用的效果
            if (this.pluginMethods[prop]) return this.pluginMethods[prop];

            if (['applyPlugins', 'ApplyPluginsType', 'EnableBy', 'ConfigChangeType', 'babelRegister', 'stage', 'ServiceStage', 'paths', 'cwd', 'pkg', 'userConfig', 'config', 'env', 'args', 'hasPlugins', 'hasPresets'].includes(prop)) {
                return typeof this[prop] === 'function' ? this[prop].bind(this) : this[prop];
            }

            return target[prop];
        }
    });
}



function registerPlugin(plugin) {
    // 考虑要不要去掉这里的校验逻辑
    // 理论上不会走到这里，因为在 describe 的时候已经做了冲突校验
    if (this.plugins[plugin.id]) {
        const name = plugin.isPreset ? 'preset' : 'plugin';
        throw new Error(`\
            ${name} ${plugin.id} is already registered by ${this.plugins[plugin.id].path}, \
            ${name} from ${plugin.path} register failed.`);
    }

    this.plugins[plugin.id] = plugin;
}


//source:  _ref预设插件节点   excluded:["presets", "plugins"]
function _objectWithoutProperties(source, excluded) {
    if (source == null) return {};
    var target = _objectWithoutPropertiesLoose(source, excluded);
    var key, i;
    if (Object.getOwnPropertySymbols) {
        var sourceSymbolKeys = Object.getOwnPropertySymbols(source);
        for (i = 0; i < sourceSymbolKeys.length; i++) {
            key = sourceSymbolKeys[i];
            if (excluded.indexOf(key) >= 0) continue;
            if (!Object.prototype.propertyIsEnumerable.call(source, key)) continue;
            target[key] = source[key];
        }
    }
    return target;
}