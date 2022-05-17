import UserApi from '@/api/user-api'

const state = () => ({
  user: null,
})

const getters = {
  user: (state) => state.user,
  authenticated: (state) => !!state.user,
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
}

export default {
  namespaced: true,
  state,
  getters,
  mutations,
  actions,
}
