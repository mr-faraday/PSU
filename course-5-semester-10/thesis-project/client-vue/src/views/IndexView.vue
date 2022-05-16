<script setup>
import { useRoute, useRouter } from 'vue-router'
import { onMounted } from 'vue'
import SpinnerIndicator from '@components/SpinnerIndicator.vue'
import UserApi from '@/api/user-api'

const router = useRouter()
const route = useRoute()

onMounted(async () => {
  await router.isReady()
  if (route.path !== '/') router.push('/')

  try {
    await UserApi.get()

    // loading

    router.push('/dashboard')
  } catch (error) {
    if (error.response.status === 401) {
      router.push('/login')
    } else {
      throw error
    }
  }
})
</script>

<template>
  <div class="container">
    <SpinnerIndicator />
  </div>
</template>

<style lang="scss" scoped>
.container {
  padding: 300px 0;
  display: flex;
  align-items: center;
  justify-content: center;
}
</style>
