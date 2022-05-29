'use strict'

const { DataTypes } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')

const name = 'Rack'

exports.Rack = db.define(name, {
    id: SERIAL,
    levelsHeight: {
        type: DataTypes.INTEGER,
        allowNull: false
    },
    postionRow: {
        type: DataTypes.INTEGER,
        allowNull: false
    }
})
