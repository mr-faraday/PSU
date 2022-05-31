import UserApi from '@/api/user-api'

const state = () => ({
  user: null,
})

/**
 * @type {import('vuex').GetterTree<*, *>}
 */
const getters = {
  info: (state) => state.user,
  authenticated: (state) => !!state.user,
  role: (state, getters, rootState, rootGetters) => {
    return rootGetters.settings.userRoles.find((r) => r.id === getters.info.roleId)
  },
}

const mutations = {
  setUser: (state, user) => (state.user = user),
}

const actions = {
  async fetch({ commit }) {
    const user = await UserApi.get()
    commit('setUser', user.data.result)

    return user.data.result
  },

  logout() {
    document.cookie = 'token=; expires=Thu, 01 Jan 1970 00:00:01 GMT; path=/'
    window.location.href = '/login'
  },
}

export default {
  namespaced: true,
  state,
  getters,
  mutations,
  actions,
}
