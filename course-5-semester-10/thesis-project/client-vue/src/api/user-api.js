import { API_URL } from '@/config'
import axios from 'axios'

const instance = axios.create({
  baseURL: API_URL,
})

export default class UserApi {
//   static async login(email, password) {
//     return instance.post('/login', { email, password })
//   }

//   static async register(email, password) {
//     return instance.post('/register', { email, password })
//   }

  static async get() {
    return instance.get('/user')
  }

//   static async updateUser(user) {
//     return instance.put('/user', user)
//   }
}
