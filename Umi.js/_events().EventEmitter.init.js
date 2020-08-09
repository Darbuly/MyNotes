function init() {
    var _this = this; //保存this


    return _asyncToGenerator(function* () { //异步严格顺序执行以下函数

        _this.setStage(_enums.ServiceStage.init); //设置当前生命周期  2:init


        _this.initPresetsAndPlugins(); // 这里收集配置中取消的预设，添加到 this.skipPluginIds忽略插件数组 中去



        _this.setStage(_enums.ServiceStage.initHooks); //设置当前生命周期  5:initHooks

        Object.keys(_this.hooksByPluginId).forEach(id => {
            const hooks = _this.hooksByPluginId[id];
            hooks.forEach(hook => {
                const key = hook.key;
                hook.pluginId = id;
                _this.hooks[key] = (_this.hooks[key] || []).concat(hook);
            });
        }); // plugin is totally ready

        _this.setStage(_enums.ServiceStage.pluginReady);

        _this.applyPlugins({
            key: 'onPluginReady',
            type: _enums.ApplyPluginsType.event
        }); // get config, including:
        // 1. merge default config
        // 2. validate


        _this.setStage(_enums.ServiceStage.getConfig);

        const defaultConfig = yield _this.applyPlugins({
            key: 'modifyDefaultConfig',
            type: _this.ApplyPluginsType.modify,
            initialValue: yield _this.configInstance.getDefaultConfig()
        });



        _this.config = yield _this.applyPlugins({
            key: 'modifyConfig',
            type: _this.ApplyPluginsType.modify,
            initialValue: _this.configInstance.getConfig({
                defaultConfig
            })
        }); // merge paths to keep the this.paths ref

        _this.setStage(_enums.ServiceStage.getPaths); // config.outputPath may be modified by plugins


        if (_this.config.outputPath) {
            _this.paths.absOutputPath = (0, _path().join)(_this.cwd, _this.config.outputPath);
        }

        const paths = yield _this.applyPlugins({
            key: 'modifyPaths',
            type: _enums.ApplyPluginsType.modify,
            initialValue: _this.paths
        });
        Object.keys(paths).forEach(key => {
            _this.paths[key] = paths[key];
        });
    })();
}