import { API_URL } from '@/config'
import axios from 'axios'

const instance = axios.create({ baseURL: `${API_URL}/auth` })

export default class AuthApi {
  static async login({ login, password }) {
    return instance.post('/login', { login, password })
  }
}
