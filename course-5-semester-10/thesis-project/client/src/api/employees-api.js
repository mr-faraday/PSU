import { API_URL } from '@/config'
import axios from 'axios'

const instance = axios.create({ baseURL: `${API_URL}/employees` })

export default class EmployeesApi {
  static async get() {
    return instance.get('/')
  }

  static async create(employee) {
    return instance.post('/', employee)
  }

  static async deactivate(id) {
    return instance.post(`/${id}/deactivate`)
  }

  static async activate(id) {
    return instance.post(`/${id}/activate`)
  }
}
