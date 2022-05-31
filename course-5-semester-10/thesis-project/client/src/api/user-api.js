import { API_URL } from '@/config'
import axios from 'axios'

const instance = axios.create({ baseURL: `${API_URL}/user` })

export default class UserApi {
  static async get() {
    return instance.get('/')
  }

  static async changePassword({ oldPassword, newPassword }) {
    return instance.post('/change-password', { oldPassword, newPassword })
  }
}
