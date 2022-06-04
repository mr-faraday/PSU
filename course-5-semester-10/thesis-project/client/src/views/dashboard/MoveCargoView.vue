<script setup>
import { ref } from 'vue'
import SpinnerIndicator from '@/components/SpinnerIndicator.vue'
import CargosApi from '@/api/cargos-api'
import MoveCargoForm from '@/components/forms/MoveCargoForm.vue'
import { useToast } from 'vue-toastification'

const toast = useToast()

const loading = ref(false)
const form = ref(null)

const moveCargo = async (cargoId) => {
  try {
    loading.value = true

    await CargosApi.return(cargoId)
    toast.success('Заявка на возврат ТМЦ успешно отправлена')

    form.value?.clearForm()
  } catch (error) {
    toast.error(error.response?.data?.message ?? error.message)
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
