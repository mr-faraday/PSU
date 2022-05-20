'use strict'

const { DataTypes } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')
const { Rack } = require('./rack')

const name = 'Shelf'

exports.Shelf = db.define(name, {
    id: SERIAL,
    shelf_number: {
        type: DataTypes.INTEGER,
        allowNull: false,
        unique: true,
        validate: {
            notEmpty: true,
            isInt: true
        }
    },
    rack_id: {
        type: DataTypes.INTEGER,
        allowNull: false,
        references: {
            model: Rack,
            key: 'id'
        }
    }
})
