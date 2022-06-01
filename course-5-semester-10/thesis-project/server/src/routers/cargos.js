'use strict'

const asyncHandler = require('express-async-handler')
const { TaskStatusId } = require('../constants')
const { db } = require('../db')
const { Cargo } = require('../db/models/cargo')
const { CargoPlacement } = require('../db/models/cargo-placement')
const { Shelf } = require('../db/models/shelf')
const { Task } = require('../db/models/task')
const router = require('express').Router()

router.use(require('../middleware/authentication-middleware'))

router.get(
    '/',
    asyncHandler(async (req, res) => {
        res.json({
            success: true,
            result: await Cargo.findAll()
        })
    })
)

router.post(
    '/',
    asyncHandler(async (req, res) => {
        const { clientId, weight } = req.body

        if (!clientId || !weight) {
            return res.status(400).json({
                success: false,
                message: 'Не указаны обязательные поля'
            })
        }

        // shelves."positionQuantity" field represents the number of positions on the shelf
        // cargo_placements contains only position of cargo on shelf
        // cargo_placements.`position` field represents the ocupied position on the shelf
        // find shelf with free positions that are not a target of new tasks (new tasks status = 1)
        const freeShelvesResult = await db.query(
            `
            SELECT id FROM shelves WHERE id NOT IN
            (
                SELECT shelf_id as id FROM
                    (
                        SELECT shelf_id, COUNT(position) AS "ocupied_position_count" FROM
                            (
                                SELECT
                                    shelf_id,
                                    position
                                FROM cargo_placements cp
                                UNION ALL
                                SELECT
                                    t.target_shelf_id as shelf_id,
                                    t.target_position as position
                                FROM tasks t WHERE t.status_id = 1
                            ) as ocupations GROUP BY shelf_id
                    ) as count_res INNER JOIN shelves ON shelves.id = shelf_id
                WHERE position_quantity <= ocupied_position_count
            )
            LIMIT 1
            `,
            { type: db.QueryTypes.SELECT }
        )

        if (!freeShelvesResult[0]) {
            return res.status(406).json({
                success: false,
                message: 'Нет свободных позиций на стеллажах'
            })
        }

        const { id: shelfId } = freeShelvesResult[0]

        const shelfeOcupationsResult = await db.query(
            `
            SELECT
                position
                FROM cargo_placements cp
                WHERE shelf_id = :shelfId
                UNION ALL
                SELECT
                    t.target_position as position
                    FROM tasks t WHERE t.status_id = 1 AND t.target_shelf_id = :shelfId
            `,
            {
                type: db.QueryTypes.SELECT,
                replacements: { shelfId }
            }
        )

        const postion = shelfeOcupationsResult
            .map(({ position }) => position)
            .reduce((acc, curr) => {
                if (acc !== curr) return acc
                return acc + 1
            }, 1)

        const cargo = await Cargo.create({ clientId, weight })
        const task = await Task.create({
            cargoId: cargo.id,
            sourceShelfId: null,
            sourcePosition: null,
            targetShelfId: shelfId,
            targetPosition: postion,
            statusId: TaskStatusId.NEW,
            createdByUserId: res.locals.user.id
        })

        res.json({
            success: true,
            result: task
        })
    })
)

router.post(
    '/:id/return',
    asyncHandler(async (req, res) => {
        const { id } = req.params

        if (!id) {
            return res.status(400).json({
                success: false,
                message: 'Не указан обязательный параметр'
            })
        }

        const cargo = await Cargo.findByPk(id)

        if (!cargo) {
            return res.status(404).json({
                success: false,
                message: 'Не найден груз'
            })
        }

        const existingTask = await Task.findOne({
            where: {
                cargoId: cargo.id,
                statusId: TaskStatusId.NEW
            }
        })

        if (existingTask) {
            return res.status(406).json({
                success: false,
                message: 'С этим грузом уже связана задача'
            })
        }

        const cargoCurrentPlacement = await CargoPlacement.findOne({
            where: { cargoId: cargo.id }
        })

        await Task.create({
            cargoId: cargo.id,
            sourceShelfId: cargoCurrentPlacement.shelfId,
            sourcePosition: cargoCurrentPlacement.position,
            targetShelfId: null,
            targetPosition: null,
            statusId: TaskStatusId.NEW,
            createdByUserId: res.locals.user.id
        })

        res.json({ success: true })
    })
)

module.exports = router
