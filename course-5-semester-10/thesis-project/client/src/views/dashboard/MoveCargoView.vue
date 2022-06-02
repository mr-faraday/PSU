<script setup>
import { ref } from 'vue'
import SpinnerIndicator from '@/components/SpinnerIndicator.vue'
import CargosApi from '@/api/cargos-api'
import MoveCargoForm from '@/components/forms/MoveCargoForm.vue';

const loading = ref(false)
const form = ref(null)

const moveCargo = async (cargoId) => {
  try {
    loading.value = true

    await CargosApi.return(cargoId)
    alert('Заявка на возврат ТМЦ успешно отправлена')

    form.value.clearForm()
  } catch (error) {
    if (error.response?.data?.message) {
      alert(error.response.data.message)
    } else {
      console.warn(error)
    }
  } finally {
    loading.value = false
  }
}
</script>

<template>
  <div v-if="loading" class="spinner-container">
    <SpinnerIndicator />
  </div>

  <div v-else class="create-client-form-container container">
    <MoveCargoForm ref="form" @submit="moveCargo" />
  </div>
</template>

<style lang="scss" scoped>
</style>
