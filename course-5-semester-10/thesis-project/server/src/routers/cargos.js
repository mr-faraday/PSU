'use strict'

const asyncHandler = require('express-async-handler')
const { TaskStatusId } = require('../constants')
const { db } = require('../db')
const { Cargo } = require('../db/models/cargo')
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
            return res.json({
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
            return res.json({
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
                    t.target_shelf_id as shelf_id,
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

module.exports = router

// `
//             SELECT
//                 s.id,
//                 s.positionQuantity,
//                 s.level_height as levelHeight,
//                 s.rack_id as rackId,
//                 r.postion_row as postionRow
//             FROM
//                 shelves s
//             LEFT JOIN
//                 racks r
//             ON
//                 s.rack_id = r.id
//             WHERE
//                 s.id NOT IN (
//                     SELECT
//                         shelf_id
//                     FROM
//                         cargo_placements
//                 )
//             ORDER BY
//                 r.postion_row,
//                 s.positionQuantity
//             `,

// const findResult = await db.query(
//     `
//     SELECT * FROM (
//         SELECT
//             shelf.id AS shelfId,
//             shelf.positionQuantity AS shelfPositionQuantity,
//             shelf.level_height AS shelfLevelHeight,
//             (
//                 SELECT
//                     COUNT(*)
//                 FROM
//                     cargo_placements AS cargo_placement
//                 WHERE
//                     cargo_placement.shelf_id = shelf.id
//             ) AS occupiedPositions
//         FROM
//             shelves as shelf
//         WHERE
//             shelf.id NOT IN (
//                 SELECT
//                     cargo_placement.shelf_id
//                 FROM
//                     cargo_placements AS cargo_placement
//                 WHERE
//                     cargo_placement.cargo_id = :cargoId
//             )
//     ) AS shelf
//     WHERE
//         shelf.occupiedPositions < shelf.shelfPositionQuantity * shelf.shelfLevelHeight
//     ORDER BY
//         shelf.occupiedPositions ASC
//     LIMIT 1
// `,
//     {
//         type: db.QueryTypes.SELECT,
//         replacements: { cargoId: 1 /* cargo.id */ }
//     }
// )
