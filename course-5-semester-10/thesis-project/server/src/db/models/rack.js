'use strict'

const { DataTypes } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')

const name = 'Rack'

exports.Rack = db.define(name, {
    id: SERIAL,
    rackNumber: {
        type: DataTypes.STRING(50),
        allowNull: false,
        unique: true,
        validate: { notEmpty: true }
    }
})
