<script setup>
import UserApi from '@/api/user-api'
import ControlPanel from '@/components/ControlPanel.vue'
import { computed, ref } from 'vue'
import { useRoute } from 'vue-router'
import { useStore } from 'vuex'

const store = useStore()
const user = computed(() => store.getters['user/info'])
const userRole = computed(() => store.getters['user/role'])

const loading = ref(false)

const currentPassword = ref('')
const newPassword = ref('')
const confirmPassword = ref('')

const changePassword = async (e) => {
  if (!currentPassword.value || !newPassword.value || !confirmPassword.value) {
    return
  }

  try {
    e.preventDefault()
    loading.value = true

    if (newPassword.value !== confirmPassword.value) {
      throw new Error('Пароли не совпадают')
    }

    await UserApi.changePassword({
      oldPassword: currentPassword.value,
      newPassword: newPassword.value,
    })

    currentPassword.value = ''
    newPassword.value = ''
    confirmPassword.value = ''

    alert('Пароль успешно изменен')
  } catch (error) {
    if (error.response?.status === 401) {
      alert('Неправильно введён текущий пароль')
    } else {
      alert(error.message)
    }
  } finally {
    loading.value = false
  }
}

const route = useRoute()
const isIndex = computed(() => /dashboard\/?$/.test(route.path))
</script>

<template>
  <div class="dashboard-page">
    <ControlPanel />

    <div v-if="isIndex" class="operation-window container">
      <h2>{{ user.firstName }} {{ user.lastName }}</h2>

      <table>
        <tr>
          <td>Роль</td>
          <td>
            {{ userRole.name }}
          </td>
        </tr>

        <tr>
          <td>Логин</td>
          <td>
            {{ user.login }}
          </td>
        </tr>
      </table>

      <form class="change-password-form" @submit="changePassword">
        <h4>Смена пароля</h4>

        <div class="form-group">
          <input v-model="currentPassword" type="password" placeholder="Текущий пароль" />
        </div>

        <div class="form-group">
          <input type="password" id="new-password" v-model="newPassword" placeholder="Новый пароль" />
        </div>

        <div class="form-group">
          <input
            type="password"
            id="confirm-password"
            v-model="confirmPassword"
            placeholder="Подтвердите пароль"
          />
        </div>

        <button type="button" @click="changePassword">Сменить</button>
      </form>
    </div>

    <div v-else class="operation-window">
      <h2 class="container">{{ route.meta.title }}</h2>

      <router-view />
    </div>
  </div>
</template>

<style lang="scss" scoped>
.dashboard-page {
  display: flex;
}

tr td:first-child {
  font-weight: bold;
  min-width: 100px;
}

.change-password-form {
  margin-top: 50px;
}
</style>
