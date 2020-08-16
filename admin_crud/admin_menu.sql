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

 Date: 09/08/2020 23:38:57
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for admin_menu
-- ----------------------------
DROP TABLE IF EXISTS `admin_menu`;
CREATE TABLE `admin_menu`  (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `desc` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `path` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `redirect` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `icon` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `authority` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `pid` int(11) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 16 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of admin_menu
-- ----------------------------
INSERT INTO `admin_menu` VALUES (1, NULL, NULL, '/', '/users-orders/orders-manage', NULL, '0', 0);
INSERT INTO `admin_menu` VALUES (2, 'admin', '用户管理', '/admin', NULL, 'crown', '1', 0);
INSERT INTO `admin_menu` VALUES (3, 'sub-page', '用户列表', '/admin/sub-page', NULL, 'OrderedList', '1', 2);
INSERT INTO `admin_menu` VALUES (4, 'product', '商品与促销', '/products', NULL, 'crown', '1,2,3,4', 0);
INSERT INTO `admin_menu` VALUES (5, 'upload-batch', '批量上货', '/products/upload-batch', NULL, 'smile', '1,2,3', 4);
INSERT INTO `admin_menu` VALUES (6, 'upload-check', '商家审核', '/products/upload-check', NULL, 'smile', '1,2', 4);
INSERT INTO `admin_menu` VALUES (7, 'upload-check-platform', '平台审核', '/products/upload-check-platform', NULL, 'smile', '1,2', 4);
INSERT INTO `admin_menu` VALUES (8, 'manage', '在售商品管理', '/products/manage', NULL, 'smile', '1,2', 4);
INSERT INTO `admin_menu` VALUES (9, 'users-orders', '用户与订单', '/users-orders', NULL, 'crown', '1,2,3', 0);
INSERT INTO `admin_menu` VALUES (10, 'orders-manage', '订单管理', '/users-orders/orders-manage', NULL, 'smile', '1,2,3', 9);
INSERT INTO `admin_menu` VALUES (11, 'crm-orders-manage', 'CRM订单管理', '/users-orders/crm-orders-manage', NULL, 'smile', '1,2,3', 9);
INSERT INTO `admin_menu` VALUES (12, 'store', '店铺管理', '/store', NULL, 'crown', '1,2', 0);
INSERT INTO `admin_menu` VALUES (13, 'store-open', '开店申请', '/store/store-open', NULL, 'smile', '1,2', 12);
INSERT INTO `admin_menu` VALUES (14, 'store-coupon', '购物券管理', '/store/store-coupon', NULL, 'smile', '1,2', 12);
INSERT INTO `admin_menu` VALUES (15, 'test', 'test', NULL, NULL, NULL, NULL, NULL);

SET FOREIGN_KEY_CHECKS = 1;
