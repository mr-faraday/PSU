import UserApi from '@/api/user-api'

const state = () => ({
  user: null,
})

const getters = {
  user: (state) => state.user,
}

const mutations = {
  setUser: (state, user) => (state.user = user),
}

const actions = {
  async getUser({ commit }) {
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
