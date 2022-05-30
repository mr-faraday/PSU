'use strict'

const { DataTypes, Model } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')
const { UserRole } = require('./user-role')
const bcrypt = require('bcrypt')

const saltRounds = 10

class User extends Model {
    async setPassword (password) {
        this.password = await bcrypt.hash(password, saltRounds)
    }

    async comparePasword (password) {
        return await bcrypt.compare(password, this.password)
    }

    /**
     * creation guard
     */
    static create () {
        throw new Error('Must be done by .setPassword() and .save()')
    }
}

User.init(
    {
        id: SERIAL,
        login: {
            type: DataTypes.STRING(255),
            allowNull: false,
            unique: true,
            validate: { notEmpty: true }
        },
        password: {
            type: DataTypes.STRING(255),
            allowNull: false,
            validate: { notEmpty: true }
        },

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

        roleId: {
            type: DataTypes.INTEGER,
            references: {
                model: UserRole,
                key: 'id'
            }
        }
    },
    { sequelize: db, modelName: 'User' }
)

exports.User = User
