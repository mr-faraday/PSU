'use strict'

const { DataTypes, Model } = require('sequelize')
const { db } = require('..')
const { SERIAL } = require('../utils/field-types')
const { EmployeeRole } = require('./employee-role')
const bcrypt = require('bcrypt')

const saltRounds = 10

class Employee extends Model {
    async setPassword (password) {
        this.password = await bcrypt.hash(password, saltRounds)
    }

    async comparePasword (hash) {
        return await bcrypt.compare(this.password, hash)
    }

    /**
     * create guard
     */
    static create () {
        throw new Error('Must be done by .setPassword() and .save()')
    }
}

Employee.init(
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
            allowNull: false,
            references: {
                model: EmployeeRole,
                key: 'id'
            }
        }
    },
    { sequelize: db, modelName: 'Employee' }
)

exports.Employee = Employee
