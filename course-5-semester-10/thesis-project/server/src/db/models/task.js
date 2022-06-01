'use strict'

const { DataTypes } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')
const { Cargo } = require('./cargo')
const { Client } = require('./client')
const { Shelf } = require('./shelf')
const { TaskStatus } = require('./task-status')
const { User } = require('./user')

const name = 'Task'

exports.Task = db.define(
    name,
    {
        id: SERIAL,
        cargoId: {
            type: DataTypes.INTEGER,
            allowNull: false,
            references: {
                model: Cargo,
                key: 'id'
            }
        },
        statusId: {
            type: DataTypes.INTEGER,
            allowNull: false,
            references: {
                model: TaskStatus,
                key: 'id'
            }
        },

        sourceShelfId: {
            type: DataTypes.INTEGER,
            references: {
                model: Shelf,
                key: 'id'
            }
        },
        sourcePosition: {
            type: DataTypes.INTEGER
        },
        targetShelfId: {
            type: DataTypes.INTEGER,
            references: {
                model: Shelf,
                key: 'id'
            }
        },
        targetPosition: {
            type: DataTypes.INTEGER
        },

        createdByUserId: {
            type: DataTypes.INTEGER,
            references: {
                model: Client,
                key: 'id'
            }
        }
    },
    { timestamps: true }
)
