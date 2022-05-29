'use strict'

const { DataTypes } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')

const name = 'Client'

exports.Client = db.define(name, {
    id: SERIAL,
    firstName: {
        type: DataTypes.STRING(255),
        allowNull: false,
        validate: { notEmpty: true }
    },
    lastName: {
        type: DataTypes.STRING(255),
        allowNull: false,
        validate: { notEmpty: true }
    },
    phone: {
        type: DataTypes.STRING(255),
        allowNull: false,
        validate: { notEmpty: true }
    }
})
