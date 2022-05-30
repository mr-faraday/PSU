import SettingsApi from '@/api/settings-api'
import { createStore } from 'vuex'
import user from './modules/user'

export default createStore({
  state: {
    settings: null,
  },
  getters: {
    settings: (state) => state.settings,
  },
  mutations: {
    setSettings: (state, settings) => (state.settings = settings),
  },
  actions: {
    async fetchSettings({ commit }) {
      const settingsRes = await SettingsApi.get()
      commit('setSettings', settingsRes.data.result)
    },
  },
  modules: { user },
})
