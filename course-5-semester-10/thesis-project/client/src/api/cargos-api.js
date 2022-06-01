import { API_URL } from '@/config'
import axios from 'axios'

const instance = axios.create({ baseURL: `${API_URL}/cargos` })

export default class CargosApi {
  static async get() {
    return instance.get('/')
  }
}
