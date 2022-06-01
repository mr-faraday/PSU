import { API_URL } from '@/config'
import axios from 'axios'

const instance = axios.create({ baseURL: `${API_URL}/cargos` })

export default class CargosApi {
  static async get() {
    return instance.get('/')
  }

  static async create(cargoData) {
    return instance.post('/', cargoData)
  }

  static async return(cargoId) {
    return instance.post(`/${cargoId}/return`)
  }
}
