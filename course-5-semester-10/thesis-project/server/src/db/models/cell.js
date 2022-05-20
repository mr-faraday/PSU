'use strict'

const { DataTypes } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')
const { Shelf } = require('./shelf')

const name = 'Cell'

exports.Shelf = db.define(name, {
    id: SERIAL,
    cell_number: {
        type: DataTypes.INTEGER,
        allowNull: false,
        unique: true,
        validate: {
            notEmpty: true,
            isInt: true
        }
    },
    shelf_id: {
        type: DataTypes.INTEGER,
        allowNull: false,
        references: {
            model: Shelf,
            key: 'id'
        }
    }
})
