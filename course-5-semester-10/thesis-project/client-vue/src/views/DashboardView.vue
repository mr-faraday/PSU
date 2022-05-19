<script setup>
import ControlPanel from '@/components/ControlPanel.vue'
import { computed } from 'vue'
import { useRoute } from 'vue-router'

const route = useRoute()
const isIndex = computed(() => /dashboard\/?$/.test(route.path))
</script>

<template>
  <div class="dashboard-page">
    <ControlPanel />

    <div v-if="isIndex" class="operation-window">
      <h2>Dashboard</h2>

      <p>Select operation in side menu</p>
    </div>

    <div v-else class="operation-window">
      <h2>{{ route.meta.title }}</h2>

      <router-view />
    </div>
  </div>
</template>

<style lang="scss" scoped>
.dashboard-page {
  display: flex;
}
</style>
