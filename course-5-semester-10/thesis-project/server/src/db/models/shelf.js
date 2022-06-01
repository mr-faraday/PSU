'use strict'

const { DataTypes } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')
const { Rack } = require('./rack')

const name = 'Shelf'

exports.Shelf = db.define(name, {
    id: SERIAL,
    rackId: {
        type: DataTypes.INTEGER,
        references: {
            model: Rack,
            key: 'id'
        }
    },
    positionQuantity: {
        type: DataTypes.INTEGER,
        allowNull: false
    },
    levelHeight: {
        type: DataTypes.INTEGER,
        allowNull: false
    }
})
