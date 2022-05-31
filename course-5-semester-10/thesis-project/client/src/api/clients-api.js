import { API_URL } from '@/config'
import axios from 'axios'

const instance = axios.create({ baseURL: `${API_URL}/clients` })

export default class ClientsApi {
  static async get() {
    return instance.get('/')
  }

  static async create(client) {
    return instance.post('/', client)
  }
}
