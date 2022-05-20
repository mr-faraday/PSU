import { API_URL } from '@/config'
import axios from 'axios'

const instance = axios.create({
  baseURL: `${API_URL}/auth`,
  withCredentials: true,
})

export default class AuthApi {
  static async login({ username, password }) {
    return instance.post('/login', { username, password })
  }
}
