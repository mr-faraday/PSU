import { API_URL } from '@/config'
import axios from 'axios'

const instance = axios.create({ baseURL: `${API_URL}/warehouse` })

export default class WarehouseApi {
  static async getShelfOcupations() {
    return instance.get('/shelf-ocupations')
  }
}
