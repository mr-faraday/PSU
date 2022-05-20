<script setup>
import AuthApi from '@/api/auth-api'
import { ref } from 'vue'
import { useRouter } from 'vue-router'
import { useStore } from 'vuex'

const router = useRouter()
const store = useStore()

const username = ref('')
const password = ref('')

const submitHandler = async (e) => {
  e.preventDefault()

  try {
    await AuthApi.login({
      username: username.value,
      password: password.value,
    })

    await store.dispatch('user/fetch')

    router.push('/dashboard')
  } catch (error) {
    console.log(error)
    alert('Invalid credentials')
  }
}
</script>

<template>
  <form class="login-form" @submit="submitHandler">
    <h2>Login</h2>

    <div class="input">
      <input v-model="username" type="text" placeholder="Username" />
    </div>

    <div class="input">
      <input v-model="password" type="password" placeholder="Password" />
    </div>

    <input type="submit" value="Login" />
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
