import { API_URL } from '@/config'
import axios from 'axios'

const instance = axios.create({ baseURL: `${API_URL}/settings` })

export default class SettingsApi {
  static async get() {
    return instance.get('/')
  }
}
