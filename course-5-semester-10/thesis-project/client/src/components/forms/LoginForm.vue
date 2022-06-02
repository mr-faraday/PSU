<script setup>
import AuthApi from '@/api/auth-api'
import { ref } from 'vue'
import { useRouter } from 'vue-router'
import { useToast } from 'vue-toastification'
import { useStore } from 'vuex'

const router = useRouter()
const store = useStore()
const toast = useToast()

const loading = ref(false)
const login = ref('')
const password = ref('')

const submitHandler = async (e) => {
  e.preventDefault()

  if (!login.value || !password.value) {
    toast.warning('Введите логин и пароль')
    return
  }

  try {
    loading.value = true

    await AuthApi.login({
      login: login.value,
      password: password.value,
    })

    await store.dispatch('user/fetch')

    router.push('/dashboard')
  } catch (error) {
    if (error.response?.status === 401) {
      toast.error('Неверный логин или пароль')
    } else {
      toast.error(error.message)
    }

    loading.value = false
  }
}
</script>

<template>
  <form class="login-form" @submit="submitHandler">
    <h2>Вход</h2>

    <div class="input">
      <input v-model="login" type="text" placeholder="Логин" :disabled="loading" />
    </div>

    <div class="input">
      <input v-model="password" type="password" placeholder="пароль" :disabled="loading" />
    </div>

    <input type="submit" value="Войти" :disabled="loading" />
  </form>
</template>

<style lang="scss" scoped>
.login-form {
  padding: 12px 32px;
  padding-bottom: 20px;
  box-shadow: 5px 5px 15px -7px rgba(0, 0, 0, 0.5);

  width: 300px;
  display: flex;
  flex-direction: column;

  h2 {
    text-align: center;
  }

  .input {
    margin-bottom: 12px;
    display: flex;

    input {
      flex: 1;
    }
  }
}
</style>
