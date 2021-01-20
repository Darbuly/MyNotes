import { Service } from 'egg';
import moment = require('moment');
/**
 * 添加
 */
interface CreateDataType {
    name: string;
    valid_start_time: string;
    valid_end_time: string;
    cycle_type: number;
    cycle_value: number;
    cycle_start_date: string;
    cycle_end_date: string;
    status: number;
    discount_rate: number;
    dec: string;
    total_quota: number;
    once_quota: number;
}


//秒杀表 service
export default class SeckillService extends Service {

    async add(req_data: CreateDataType) {

        const { ctx } = this;
        let transaction: any;
        try {
            // 建立事务对象
            transaction = await this.ctx.model.transaction();

            // 添加秒杀表
            const seckill_info = await ctx.model.Seckill.create({
                ...req_data
            }, {
                transaction,
            })
            // const seckill_info = await ctx.model.query('insert into seckill (name,dec,valid_start_time,valid_end_time,cycle_type,cycle_value,cycle_start_date,cycle_end_date,status,discount_rate,total_quota,once_quota)')
            // 批量处理 秒杀详情表 seckill_detail
            await this.commonAdd(req_data, seckill_info.id, transaction);

            // 提交事务
            await transaction.commit();

            return {
                code: 201,
                msg: '添加成功'
            };

        } catch (e) {
            // 事务回滚     
            await transaction.rollback();
            throw new Error(e);
        }
    }

    async commonAdd(req_data: CreateDataType, seckill_id: number, transaction: any) {
        try {
            let sql_arr: string[] = [];
            let startDayMoment: any = null;
            let endDayMoment: any = null;
            let endMoment: any = null;
            let last_dayMonent: any = null;
            let start_Moment: any = null;
            let firstStartDayMoment: any = null;
            let sql: string = '';

            switch (req_data.cycle_type) {
                // 周期：0为一次性，1小时，2天，3周，4月
                case 0:
                    await this.ctx.model.SeckillDetail.create({
                        date: req_data.cycle_start_date,
                        valid_start_time: req_data.valid_start_time,
                        valid_end_time: req_data.valid_end_time,
                        seckill_id,
                        cycle_type: req_data.cycle_type
                    }, {
                        transaction
                    })
                    break;

                case 1:

                    //遍历天
                    startDayMoment = moment(req_data.cycle_start_date);
                    endDayMoment = moment(req_data.cycle_end_date);
                    endMoment = moment(moment().format('L') + ' 24:00:00');

                    last_dayMonent = startDayMoment;
                    while (last_dayMonent <= endDayMoment) {
                        //遍历时间
                        let last_Moment = moment(req_data.valid_start_time)
                        if (last_Moment.isValid()) {
                            while ((last_Moment < endMoment)) {
                                sql_arr.push(`('${last_dayMonent.format('YYYY-MM-DD')}','${last_Moment.format('HH:mm:ss')}','${last_Moment.add(req_data.cycle_value, 'hours').format('HH:mm:ss')}',${seckill_id},${req_data.cycle_type})`)
                            }
                        }
                        last_dayMonent = last_dayMonent.add(1, 'days');
                    }
                    sql = 'INSERT INTO seckill_detail (date,valid_start_time,valid_end_time,seckill_id,cycle_type) values ';
                    if (sql_arr.length) {
                        sql += sql_arr.join(',') + ';'
                        await this.ctx.model.query(sql, { transaction });
                    }

                    break;

                case 2:
                    sql_arr = [];
                    startDayMoment = moment(req_data.cycle_start_date);
                    endDayMoment = moment(req_data.cycle_end_date);
                    start_Moment = moment(req_data.valid_start_time);
                    endMoment = null;
                    //是否指定了结束时段
                    if (req_data.valid_end_time && moment(req_data.valid_start_time) < moment(req_data.valid_end_time)) {
                        endMoment = moment(req_data.valid_end_time);
                    }
                    if (req_data.cycle_value <= 0) {
                        return false;
                    }
                    last_dayMonent = startDayMoment;
                    while (last_dayMonent <= endDayMoment) {
                        sql_arr.push(`('${last_dayMonent.format('YYYY-MM-DD')}','${start_Moment.format('HH:mm:ss')}',${endMoment ? `'${endMoment.format('HH:mm:ss')}'` : 'NULL'}, ${seckill_id},${req_data.cycle_type})`)
                        last_dayMonent = last_dayMonent.add(req_data.cycle_value, 'days');
                    }
                    sql = 'INSERT INTO seckill_detail (date,valid_start_time,valid_end_time,seckill_id,cycle_type) values ';
                    if (sql_arr.length) {
                        sql += sql_arr.join(',') + ';'
                        await this.ctx.model.query(sql, { transaction });
                    }
                    break;

                case 3:
                    sql_arr = [];
                    startDayMoment = moment(req_data.cycle_start_date);

                    //算出活动开始日期的之后的第一个周X时间
                    if (req_data.cycle_value <= 0) {
                        return false;
                    }
                    firstStartDayMoment = startDayMoment.subtract(startDayMoment.format('E') - req_data.cycle_value - 7, 'days');
                    endDayMoment = moment(req_data.cycle_end_date);

                    start_Moment = moment(req_data.valid_start_time);
                    endMoment = null;
                    //是否指定了结束时段
                    if (req_data.valid_end_time && moment(req_data.valid_start_time) < moment(req_data.valid_end_time)) {
                        endMoment = moment(req_data.valid_end_time);
                    }

                    last_dayMonent = firstStartDayMoment;
                    while (last_dayMonent <= endDayMoment) {
                        sql_arr.push(`('${last_dayMonent.format('YYYY-MM-DD')}','${start_Moment.format('HH:mm:ss')}',${endMoment ? `'${endMoment.format('HH:mm:ss')}'` : 'NULL'}, ${seckill_id},${req_data.cycle_type})`)
                        last_dayMonent = last_dayMonent.add(7, 'days');//7天为一周
                    }
                    sql = 'INSERT INTO seckill_detail (date,valid_start_time,valid_end_time,seckill_id,cycle_type) values ';
                    if (sql_arr.length) {
                        sql += sql_arr.join(',') + ';'
                        await this.ctx.model.query(sql, { transaction });
                    }
                    break;
                case 4:
                    sql_arr = [];
                    startDayMoment = moment(req_data.cycle_start_date);

                    //算出活动开始日期的之后的第一个月的X号
                    if (req_data.cycle_value <= 0) {
                        return false;
                    }
                    firstStartDayMoment = startDayMoment.subtract(startDayMoment.format('D') - req_data.cycle_value, 'days');
                    endDayMoment = moment(req_data.cycle_end_date);

                    start_Moment = moment(req_data.valid_start_time);
                    endMoment = null;
                    //是否指定了结束时段
                    if (req_data.valid_end_time && moment(req_data.valid_start_time) < moment(req_data.valid_end_time)) {
                        endMoment = moment(req_data.valid_end_time);
                    }

                    last_dayMonent = firstStartDayMoment;
                    while (last_dayMonent <= endDayMoment) {
                        sql_arr.push(`('${last_dayMonent.format('YYYY-MM-DD')}','${start_Moment.format('HH:mm:ss')}',${endMoment ? `'${endMoment.format('HH:mm:ss')}'` : 'NULL'}, ${seckill_id},${req_data.cycle_type})`)
                        last_dayMonent = last_dayMonent.add(1, 'months');//7天为一周
                    }
                    sql = 'INSERT INTO seckill_detail (date,valid_start_time,valid_end_time,seckill_id,cycle_type) values ';
                    if (sql_arr.length) {
                        sql += sql_arr.join(',') + ';'
                        await this.ctx.model.query(sql, { transaction });
                    }
                    break;

            }
        } catch (e) {
            throw new Error(e);
        }

    }
}
