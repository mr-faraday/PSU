import { API_URL } from '@/config'
import axios from 'axios'

const instance = axios.create({ baseURL: `${API_URL}/tasks` })

export default class TasksApi {
  static async get() {
    return instance.get('/')
  }
}
