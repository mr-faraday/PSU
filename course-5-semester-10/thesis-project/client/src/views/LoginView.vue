<script setup>
import LoginForm from '@/components/forms/LoginForm.vue'
</script>

<template>
  <div class="login-page">
    <div class="login-form-container">
      <LoginForm />
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
