const { db } = require('..')

const getAll = async () => {
    return await db.query(
        `
        SELECT * FROM (
            SELECT
                id,
                rack_id as "rackId",
                position_quantity as "positionQuantity",
                level_height as "levelHeight",
                COALESCE(ocupied_position_count, 0) as "ocupiedPositionCount"
            FROM shelves LEFT JOIN (
                SELECT shelf_id, COUNT(position) AS ocupied_position_count FROM (
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
            ) as ocupations ON shelves.id = ocupations.shelf_id
        ) as res ORDER BY res."ocupiedPositionCount" ASC
        `,
        { type: db.QueryTypes.SELECT }
    )
}

const getNotFull = async () => {
    return await db.query(
        `
        SELECT * FROM (
            SELECT
                id,
                rack_id as "rackId",
                position_quantity as "positionQuantity",
                level_height as "levelHeight",
                COALESCE(ocupied_position_count, 0) as "ocupiedPositionCount"
            FROM shelves LEFT JOIN (
                SELECT shelf_id, COUNT(position) AS ocupied_position_count FROM (
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
            ) as ocupations ON shelves.id = ocupations.shelf_id
        ) as res WHERE res."ocupiedPositionCount" < res."positionQuantity"
        ORDER BY res."ocupiedPositionCount" ASC
        `,
        { type: db.QueryTypes.SELECT }
    )
}

exports = module.exports.ShelfOcupation = {
    getAll,
    getNotFull
}
