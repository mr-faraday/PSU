<script setup>
import { useRouter } from 'vue-router'
import LoginForm from '@/components/forms/LoginForm.vue'

const router = useRouter()

const onLogin = () => {
  router.push('/dashboard')
}
</script>

<template>
  <div class="login-page">
    <div class="login-form-container">
      <LoginForm @login="onLogin" />
    </div>
  </div>
</template>

<style lang="scss" scoped>
.login-page {
  padding: var(--vertical-padding) var(--horizontal-padding);
  padding-top: 64px;

  display: flex;
  flex-direction: column;
  align-items: center;

  .login-form-container {
    margin-bottom: 64px;
  }
}
</style>
