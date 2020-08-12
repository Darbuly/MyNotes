/*
 Navicat Premium Data Transfer

 Source Server         : jieyi_order_local
 Source Server Type    : MySQL
 Source Server Version : 50726
 Source Host           : localhost:3306
 Source Schema         : jieyi_order_local

 Target Server Type    : MySQL
 Target Server Version : 50726
 File Encoding         : 65001

 Date: 09/08/2020 23:38:50
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for admin_tbls
-- ----------------------------
DROP TABLE IF EXISTS `admin_tbls`;
CREATE TABLE `admin_tbls`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `map_obj` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '前端映射对象,不能重名',
  `table_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '数据库中对应的表名/模型',
  `updated_at` datetime(0) NULL DEFAULT NULL,
  `created_at` datetime(0) NOT NULL,
  `column_json` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '对应的列表字段JSON数据文件名',
  `status` int(10) NULL DEFAULT 1,
  PRIMARY KEY (`id`, `map_obj`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 2 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of admin_tbls
-- ----------------------------
INSERT INTO `admin_tbls` VALUES (1, 'crmorder', 'crmOrder', '2020-08-09 21:46:27', '2020-08-09 21:46:31', 'crm_order', 1);

SET FOREIGN_KEY_CHECKS = 1;
