/**初始化 预设preset 和 插件plugin
 * 
 * 
 * 生命周期： 2: 'init'
 * 
 */

function initPresetsAndPlugins() {

    /**
     * initPresets
     */
    this.setStage(_enums.ServiceStage.initPresets); //设置当前生命周期  3: 'initPresets', 
    this._extraPlugins = [];

    while (this.initialPresets.length) {
        this.initPreset(this.initialPresets.shift());
    }

    /**
     * initPlugins
     */
    this.setStage(_enums.ServiceStage.initPlugins); //设置当前生命周期  3: 'initPlugins', 

    this._extraPlugins.push(...this.initialPlugins);

    while (this._extraPlugins.length) {
        this.initPlugin(this._extraPlugins.shift());
    }
}