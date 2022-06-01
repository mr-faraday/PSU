'use strict'

const asyncHandler = require('express-async-handler')
const { UserRoleId, TaskStatusId } = require('../constants')
const { CargoPlacement } = require('../db/models/cargo-placement')
const { Task } = require('../db/models/task')
const { assert } = require('../utils/assertion')
const router = require('express').Router()

router.use(require('../middleware/authentication-middleware'))

router.get(
    '/',
    asyncHandler(async (req, res) => {
        res.json({
            success: true,
            result: await Task.findAll()
        })
    })
)

router.post(
    '/:id/complete',
    asyncHandler(async (req, res) => {
        const { id } = req.params
        const user = res.locals.user

        if (![UserRoleId.ADMIN, UserRoleId.MANAGER].includes(user.roleId)) {
            return res.status(403).json({
                success: false,
                message: 'Недостаточно прав'
            })
        }

        const task = await Task.findByPk(id)

        if (!task) {
            return res.status(404).json({
                success: false,
                message: 'Задача не найдена'
            })
        }

        const { sourceShelfId, sourcePosition, targetShelfId, targetPosition } =
            task

        if (!targetPosition) {
            const placement = await CargoPlacement.findOne({
                where: {
                    cargoId: task.cargoId,
                    shelfId: sourceShelfId,
                    position: sourcePosition
                }
            })

            assert(placement, 'Не удалось найти место погрузки')
            await placement.destroy()
        } else if (!sourcePosition) {
            await CargoPlacement.create({
                cargoId: task.cargoId,
                shelfId: targetShelfId,
                position: targetPosition
            })
        } else {
            const placement = await CargoPlacement.findOne({
                where: {
                    cargoId: task.cargoId,
                    shelfId: sourceShelfId,
                    position: sourcePosition
                }
            })

            assert(placement, 'Не удалось найти место погрузки')
            await placement.update({
                shelfId: targetShelfId,
                position: targetPosition
            })
        }

        task.statusId = TaskStatusId.DONE
        await task.save()

        res.json({
            success: true,
            result: task
        })
    })
)

module.exports = router
